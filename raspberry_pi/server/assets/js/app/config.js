const app = angular.module('dreambedded')

app.run([
  'Socket',
  (Socket) => {
    Socket.init(io());

    setInterval(() => {
      let payload = [(new Date()).toString(), "none", "status"]
      Socket.getSocket().emit("heartbeat", payload.join("::"))
    }, 1500)

    Socket.getSocket().on('device_status', (message) => {
      let args = message.split("::")

      let controller = angular.element(`#device_${args[0]}`).controller('device')
      controller.onDeviceStatus(args[1])
    })
  }
])
