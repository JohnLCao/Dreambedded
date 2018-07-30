const app = angular.module('dreambedded')

import template from './device.hamlc'

app.directive('device', [
  'Socket',
  (Socket) => {
    return {
      link: (scope, element, attr) => {
        setInterval(() => {
          let payload = ["device", scope.device.pin.toString(), "device_status"]
          Socket.getSocket().emit("action", payload.join("::"))
        }, 1000)
      },
      template: template(),
      scope: {
        device: "="
      },
      controller: [
        'Socket',
        '$element',
        '$scope',
        (Socket, $element, $scope) => {
          let controller = {}

          let _isOutOfSync = (status) => {
            return $scope.deviceMode && status == "off" ||
              !$scope.deviceMode && status == "on"
          }

          controller.onModeChange = (device, modeOn) => {
            let msg = modeOn ? "device_on" : "device_off"
            let payload = ["device", "::", device.pin, "::", msg].join("")
            Socket.getSocket().emit("action", payload)
          }

          controller.onDeviceStatus = (status) => {
            if (_isOutOfSync(status)) {
              $scope.$apply(() => {
                angular.element($element).find(".mdl-switch").trigger("click")
                $scope.deviceMode = status == "on"
              })
            }
          }

          return controller
        }
      ],
      controllerAs: "devCtrl"
    }
  }
])
