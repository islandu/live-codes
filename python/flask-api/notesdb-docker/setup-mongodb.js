var connection = connect("localhost:27017/admin");
var db = connection.getSiblingDB('userdata');

db.createCollection('users');
db.users.insert([
    {
        username: 'marty',
        passwordHash: '51da16695a76d954d738259f9143ac80fb5d4149064967a0eafeb30990abeeb1', // solarwinds123
        passwordSalt: '67679ced8e63e1f3bd547efb51a5621e'
    },
    {
        username: 'ryan',
        passwordHash: '04259f293a4f7e8e910dd4de8158554b65565083dcf4f6bb0606446b1f87e806', // password123
        passwordSalt: '4c3d46459e49514250f891bd4f8ea3e9'
    }
]);

const userId = db.users.findOne({ username: 'marty' })._id

db.createCollection('notes');

db.notes.insert([
    {
        userId,
        created: '1985-10-12T00:00:00.000Z',
        modified: '1985-10-12T00:00:00.000Z',
        contents: 'Reminder: Warn Doc at Twin Pines Mall'
    },
    {
        userId,
        created: '1955-11-05T00:00:00.000Z',
        modified: '1955-11-05T00:00:00.000Z',
        contents: 'Reminder: Make it back to the clock tower by 10:04 PM'
    }
])
