const app = angular.module('dreambedded')

app.controller('DevicesCtrl', [
  '$scope',
  'DeviceStore',
  ($scope, DeviceStore) => {
    let controller = {}

    controller.create = (device) => {
      let id = DeviceStore.create(device)
      device.id = id
    }

    return controller
  }
])
