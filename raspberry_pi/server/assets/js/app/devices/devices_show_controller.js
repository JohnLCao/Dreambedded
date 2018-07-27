const app = angular.module('dreambedded')

app.controller('DevicesShowCtrl', [
  '$scope',
  '$stateParams',
  ($scope, $stateParams) => {
    let controller = {}

    controller.create = (device) => {
      console.log(device)
    }

    return controller
  }
])
