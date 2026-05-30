import json
import os
import pathlib
import re
import subprocess
import tempfile
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import urlparse


ROOT = pathlib.Path(__file__).resolve().parent
N = 15


HARNESS = r'''
#include <bits/stdc++.h>
using namespace std;

{user_code}

int main() {{
    vector<vector<int>> grid(15, vector<int>(15, 0));
    generate_shape(grid);
    for (int i = 0; i < 15; ++i) {{
        for (int j = 0; j < 15; ++j) {{
            if (j) cout << ' ';
            cout << grid[i][j];
        }}
        cout << '\n';
    }}
    return 0;
}}
'''


def normalize_grid(raw):
    nums = [int(x) for x in re.findall(r"-?\d+", raw)]
    if len(nums) != N * N:
        raise ValueError(f"Program must print exactly 225 integers, got {len(nums)}")
    return [nums[i * N:(i + 1) * N] for i in range(N)]


def judge(out_grid, target):
    matched = 0
    invalid = 0
    for i in range(N):
        for j in range(N):
            out = out_grid[i][j]
            if out != 0 and not (1 <= out <= 10):
                invalid += 1
                continue
            matched += int(out == target[i][j])
    wrong = N * N - matched
    return matched, wrong, invalid


def compile_and_run(code):
    if "generate_shape" not in code:
        raise ValueError("Code must define generate_shape(vector<vector<int>>& grid)")
    if re.search(r"\bint\s+main\s*\(", code):
        raise ValueError("Do not define main(); only complete generate_shape().")

    with tempfile.TemporaryDirectory(prefix="voxel_", dir=ROOT) as tmp:
        tmpdir = pathlib.Path(tmp)
        src = tmpdir / "main.cpp"
        exe = tmpdir / "main.exe"
        src.write_text(HARNESS.format(user_code=code), encoding="utf-8")
        compile_proc = subprocess.run(
            ["g++", "-std=c++20", "-O0", str(src), "-o", str(exe)],
            cwd=ROOT,
            capture_output=True,
            text=True,
            timeout=20,
        )
        if compile_proc.returncode != 0:
            raise RuntimeError(compile_proc.stderr or compile_proc.stdout or "Compile error")
        run_proc = subprocess.run(
            [str(exe)],
            cwd=tmpdir,
            capture_output=True,
            text=True,
            timeout=3,
        )
        if run_proc.returncode != 0:
            raise RuntimeError(run_proc.stderr or run_proc.stdout or "Runtime error")
        return normalize_grid(run_proc.stdout), run_proc.stderr


class Handler(SimpleHTTPRequestHandler):
    extensions_map = {
        **SimpleHTTPRequestHandler.extensions_map,
        ".html": "text/html; charset=utf-8",
        ".js": "text/javascript; charset=utf-8",
        ".css": "text/css; charset=utf-8",
    }

    def translate_path(self, path):
        clean = urlparse(path).path.lstrip("/") or "index.html"
        return str(ROOT / clean)

    def end_headers(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.send_header("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0")
        self.send_header("Pragma", "no-cache")
        self.send_header("Expires", "0")
        super().end_headers()

    def send_json(self, data, status=200):
        body = json.dumps(data, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_POST(self):
        if urlparse(self.path).path != "/api/run":
            return self.send_json({"error": "Not found"}, 404)
        try:
            length = int(self.headers.get("Content-Length", "0"))
            data = json.loads(self.rfile.read(length).decode("utf-8"))
            code = data.get("code", "")
            target = data.get("target", [])
            if not isinstance(code, str) or not code.strip():
                raise ValueError("Source code is empty")
            if len(target) != N or any(len(row) != N for row in target):
                raise ValueError("Invalid target grid")
            target = [[v if 1 <= int(v) <= 10 else 0 for v in row] for row in target]
            grid, stderr = compile_and_run(code)
            matched, wrong, invalid = judge(grid, target)
            self.send_json({
                "grid": grid,
                "matched": matched,
                "wrong": wrong,
                "invalid": invalid,
                "ok": wrong == 0,
                "log": stderr.strip(),
            })
        except Exception as exc:
            self.send_json({"error": str(exc)}, 400)

    def do_OPTIONS(self):
        self.send_response(204)
        self.end_headers()


def main():
    host = os.environ.get("HOST", "127.0.0.1")
    port = int(os.environ.get("PORT", "8787"))
    httpd = ThreadingHTTPServer((host, port), Handler)
    print(f"VoxelCode judge: http://{host}:{port}")
    httpd.serve_forever()


if __name__ == "__main__":
    main()
