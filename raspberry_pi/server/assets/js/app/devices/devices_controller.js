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

    controller.getDevices = () => {
      return DeviceStore.getDevices()
    }

    return controller
  }
])
