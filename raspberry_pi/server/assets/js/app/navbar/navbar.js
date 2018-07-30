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
      template: template()
    }
  }
])
