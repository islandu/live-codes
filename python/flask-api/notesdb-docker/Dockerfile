# Use official MongoDB image as base image
FROM mongo:latest

# Copy the MongoDB setup script to the container
COPY setup-mongodb.js /docker-entrypoint-initdb.d/
