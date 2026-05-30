FROM python:3.12-slim

RUN apt-get update \
  && apt-get install -y --no-install-recommends g++ \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

ENV HOST=0.0.0.0
CMD ["python", "server.py"]
