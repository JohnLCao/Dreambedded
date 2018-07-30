const app = angular.module('dreambedded')

app.controller('DevicesShowCtrl', [
  '$scope',
  '$stateParams',
  'device',
  ($scope, $stateParams, device) => {
    $scope.device = device
    let controller = {}
    return controller
  }
])
