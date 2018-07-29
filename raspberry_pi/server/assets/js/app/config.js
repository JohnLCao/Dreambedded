const app = angular.module('dreambedded')

app.run([
  'Socket',
  (Socket) => {
    Socket.init(io());

    setInterval(() => {
      let payload = [(new Date()).toString(), "none", "status"]
      Socket.getSocket().emit("heartbeat", payload.join("::"))
    }, 1500)
  }
])
