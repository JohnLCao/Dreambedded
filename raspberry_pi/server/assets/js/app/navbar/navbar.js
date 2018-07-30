const app = angular.module('dreambedded')

import template from './navbar.hamlc'

app.directive('navbar', [
  'Socket',
  'DeviceStore',
  (Socket, DeviceStore) => {
    return {
      link: (scope, element, attr) => {
        scope.devices = DeviceStore.getDevices()
      },
      controller: [
        '$scope',
        '$state',
        ($scope, $state) => {
          let controller = {}

          controller.clearDevices = () => {
            window.localStorage.clear()
            $state.go('devices.index')
          }

          return controller
        }
      ],
      template: template(),
      controllerAs: 'devCtrl'
    }
  }
])
