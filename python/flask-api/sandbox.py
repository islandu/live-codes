import pymongo
import json

client = pymongo.MongoClient('localhost:27017', connectTimeoutMS=500, serverSelectionTimeoutMS=500)
# print(client.list_database_names())

db = client['userdata']
collection = db['notes']
print(type(collection))

notes = collection.find()

for n in notes:
    n['_id'] = str(n['_id'])
    n['userId'] = str(n['userId'])
    print(json.dumps(n, indent=2))

# for user in collection.find():
#     user['_id'] = str(user['_id'])
#     # print(user)
#     print(json.dumps(user, indent=2))
#     # print('end of loop')

client.close()

# # MongoDB connection string (replace with your connection string)
# mongo_uri = "mongodb://appuser:solarwinds123@localhost:27017"

# # Initialize a MongoClient with the connection string
# client = pymongo.MongoClient(mongo_uri, connectTimeoutMS=3000, timeoutMS=3000, socketTimeoutMS=3000)
# print('connected')
# # Reference the "userdata" database
# db = client["userdata"]
# print(db)
# # Reference the "users" collection
# users_collection = db["users"]
# print(users_collection)
# # Query the collection (e.g., find all users with age greater than 25)
# query = {"username": "dt-hbtn"}
# results = users_collection.find_one(query)
# print('ran query')
# # Print the query results
# print(results)

# # Close the MongoDB connection
# client.close()
