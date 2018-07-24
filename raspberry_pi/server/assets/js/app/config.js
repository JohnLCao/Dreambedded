const app = angular.module('dreambedded')

app.run([
  'Socket',
  (Socket) => {
    Socket.init(io());

    setInterval(() => {
      Socket.getSocket().emit("heartbeat", (new Date()).toString())
    }, 1500)
  }
])
