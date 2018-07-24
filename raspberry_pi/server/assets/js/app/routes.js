const app = angular.module('dreambedded')

import devicesRootTemplate from './devices/root.hamlc'
import devicesShowTemplate from './devices/show.hamlc'

app.config([
  '$locationProvider',
  ($locationProvider) => {
    $locationProvider.html5Mode(true)
    $locationProvider.hashPrefix('!')
  }
])

app.config([
  '$stateProvider',
  ($stateProvider) => {
    $stateProvider
    .state('devices', {
      abstract: true,
      controller: 'DevicesCtrl',
      template: devicesRootTemplate()
    })
    .state('index', {
      url: '?/',
      controller: [
        '$state',
        ($state) => {
          $state.go('devices.show', { device_name: "hello" });
        }
      ]
    })
    .state('devices.show', {
      url: '/devices/:device_name',
      views: {
        '': {
          controller: 'DevicesShowCtrl',
          template: devicesShowTemplate()
        }
      }
    })
  }
]);
