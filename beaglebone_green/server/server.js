const express = require('express')
const app = express()
const PORT = 3000
const server = require('http').createServer(app)
const io = require('socket.io')(server);

app.use(express.static('public'))
app.set('view engine', 'pug')

app.get('/', (req, resp) => {
  resp.render('index')
})

io.on('connection', () => {
  console.log("new connection!!!")
})

server.listen(PORT, () =>
  console.log(`Example app listening on port ${PORT}!`)
)
