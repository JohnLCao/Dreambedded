const Bridge = require('./lib/bridge')
const Handlers = require('./lib/handlers')
const express = require('express')
const app = express()
const PORT = 8088
const server = require('http').createServer(app)
const io = require('socket.io')(server);

app.use(express.static('public'))
app.set('view engine', 'pug')

app.get('/*', (req, resp) => {
  resp.render('index')
})

io.on('connection', (client) => {
  client.on('heartbeat', (message) => {
    Bridge.send("heartbeat", message)
  })

  client.on('action', Handlers.__logger(Handlers.action))


  Bridge.onAck(function(type, msg) {
    client.emit(type, msg)
  })
})

server.listen(PORT, () =>
  console.log(`Example app listening on port ${PORT}!`)
)
