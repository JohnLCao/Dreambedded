const dgram = require('dgram')
const client = dgram.createSocket('udp4')
const PORT = 22222
const HOST = '127.0.0.1'

const Bridge = {
  onAck(callback) {
    client.on('message', (msg, rinfo) => {
      const args = msg.toString("utf8").split(":")
      const type = args[0]
      const payload = args.slice(1).join(":")

      callback(type, payload)
    })
  },

  send(messageType, payload, errorCallback) {
    const buffer = Buffer.from([messageType, payload].join("::"))

    client.send(buffer, 0, buffer.length, PORT, HOST, (err, bytes) => {
        if (err) {
          errorCallback(err)
          return
        }

        console.log(`UDP message sent to ${HOST}:${PORT}`, messageType, payload)
    })
  }
}

module.exports = Bridge
