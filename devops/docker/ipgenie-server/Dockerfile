# FROM: Indicates the base image and version to build on top of
FROM rust:1.73

# WORKDIR: Sets the image working directory for subsequent build instructions
WORKDIR /usr/src/ipgenie

# COPY: Copies files from local machine into image (local path, destination path in image)
COPY . .

# RUN: Executes a shell command
RUN cargo install --path .

# CMD: Specifies the command and arguments to run when a container is created
CMD ["ipgenie-server"]
