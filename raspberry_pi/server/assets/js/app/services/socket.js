const app = angular.module('dreambedded')

app.service('Socket', [
  () => {
    let _socket = null
    let api = {}

    api.init = (socket) => {
      _socket = socket
    }

    api.getSocket = () => {
      return _socket
    }

    return api
  }
])
