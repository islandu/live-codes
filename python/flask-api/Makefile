DB_IMAGE := notesdb
DB_CONTAINER := notesdb-01

.PHONY := api-run db-run db-build clean

api-run: db-run
	@./notes_api.py

db-run: db-build
	@sudo docker inspect $(DB_CONTAINER) > /dev/null \
		|| sudo docker run -p 27017:27017 --name $(DB_CONTAINER) -d $(DB_IMAGE):latest > /dev/null

db-build:
	@sudo docker inspect $(DB_CONTAINER) > /dev/null \
		|| sudo docker build -t $(DB_IMAGE) ./notesdb-docker > /dev/null

clean:
	@sudo docker inspect $(DB_CONTAINER) > /dev/null \
		&& sudo docker kill $(DB_CONTAINER) > /dev/null \
		&& sudo docker rm $(DB_CONTAINER) > /dev/null \
		&& sudo docker rmi $(DB_IMAGE) > /dev/null
