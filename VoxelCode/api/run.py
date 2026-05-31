import json
import os
import pathlib
import re
import shutil
import subprocess
import tempfile
from http.server import BaseHTTPRequestHandler


N = 15

HARNESS = r'''
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
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
    if not shutil.which("g++"):
        raise RuntimeError("g++ is not available in this deployment runtime.")

    with tempfile.TemporaryDirectory(prefix="voxel_") as tmp:
        tmpdir = pathlib.Path(tmp)
        src = tmpdir / "main.cpp"
        exe = tmpdir / "main"
        src.write_text(HARNESS.format(user_code=code), encoding="utf-8")
        compile_proc = subprocess.run(
            ["g++", "-std=c++20", "-O0", str(src), "-o", str(exe)],
            cwd=tmpdir,
            capture_output=True,
            text=True,
            timeout=60,
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


class handler(BaseHTTPRequestHandler):
    def send_json(self, data, status=200):
        body = json.dumps(data, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Cache-Control", "no-store")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_POST(self):
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

    def do_GET(self):
        self.send_json({"ok": True, "message": "Use POST /api/run"})
