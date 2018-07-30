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
        '$interpolate',
        (Socket, $element, $scope, $interpolate) => {
          let controller = {}

          let MESSAGES = {
            on: `Hello Dr. Brian, Power plug at pin ${$scope.device.pin} going on!`,
            off: `Hello Dr. Brian, Power plug at pin ${$scope.device.pin} going off!`
          }

          let _speak = (status) => {
            let msg;

            if (!!$scope.device.message) {
              msg = $interpolate($scope.device.message)($scope)
            } else {
              msg = MESSAGES[status]
            }

            responsiveVoice.speak(msg)
          }

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
                $scope.device.status = status
                $scope.deviceMode = status == "on"
                _speak(status)
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
