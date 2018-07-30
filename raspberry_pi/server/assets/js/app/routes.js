const app = angular.module('dreambedded')

import devicesRootTemplate from './devices/root.hamlc'
import devicesShowTemplate from './devices/show.hamlc'
import devicesNewTemplate from './devices/new.hamlc'
import devicesIndexTemplate from './devices/index.hamlc'

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
      controllerAs: 'devCtrl',
      template: devicesRootTemplate()
    })
    .state('index', {
      url: '?/',
      controller: [
        '$state',
        ($state) => {
          $state.go('devices.index')
        }
      ]
    })
    .state('devices.new', {
      url: '/devices/new',
      views: {
        '':{
          template: devicesNewTemplate()
        }
      }
    })
    .state('devices.index', {
      url: '/devices',
      views: {
        '':{
          template: devicesIndexTemplate(),
          controller: [
            '$scope',
            'DeviceStore',
            ($scope, DeviceStore) => {
              $scope.devices = DeviceStore.getDevices()
            }
          ]
        }
      }
    })
    .state('devices.show', {
      url: '/devices/:device_id',
      views: {
        '': {
          controller: 'DevicesShowCtrl',
          template: devicesShowTemplate(),
          controllerAs: 'devShowCtrl',
          resolve: {
            device: [
              'DeviceStore',
              '$stateParams',
              (DeviceStore, $stateParams) => {
                return DeviceStore.getDevices().filter((ob) => { return ob.id == $stateParams.device_id })[0]
              }
            ]
          }
        }
      }
    })
  }
]);
