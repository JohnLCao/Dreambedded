const app = angular.module('dreambedded')

app.controller('DevicesCtrl', [
  '$scope',
  'DeviceStore',
  '$state',
  'Socket',
  ($scope, DeviceStore, $state, Socket) => {
    let controller = {}

    controller.create = (device) => {
      if(DeviceStore.create(device)) {
        $state.go('devices.index')
      }
    }

    controller.onModeChange = (device, modeOn) => {
      let msg = modeOn ? "device_on" : "device_off"
      let payload = ["device", "::", device.pin, "::", msg].join("")
      Socket.getSocket().emit("action", payload)
    }

    return controller
  }
])
