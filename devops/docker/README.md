# `devops/docker`

## Abstract
A sample project with `Dockerfile`s that define image builds for a simple web-server (Rust/actix_web) and a simple nginx proxy.
A `docker-compose.yml` file is included to instantiate and network the two containers.

## Usage
To run the containers execute the following command (must run with root privileges):
```
docker compose up
```
Once the containers are running, you can navigate to `http://localhost/` in a web browser to test the demo application.

## Code
```
devops/docker
├── docker-compose.yml
├── ipgenie-proxy
│   ├── Dockerfile
│   └── proxy.conf
├── ipgenie-server
│   ├── Cargo.lock
│   ├── Cargo.toml
│   ├── Dockerfile
│   ├── src
│   │   └── main.rs
│   └── www
│       ├── css
│       │   └── style.css
│       ├── index.html
│       └── js
│           └── clientInfo.js
└── README.md
```