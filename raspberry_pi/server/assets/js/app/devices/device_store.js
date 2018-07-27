const app = angular.module('dreambedded')

app.service('DeviceStore', [
  () => {

    let _devices = {}
    let _store = window.localStorage
    let _storeKey = 'dreambedded:devices'
    let api  = {}
    window.DeviceStore = api

    let _generateId = () => {
      return (Math.random().toString(36).substring(2,10) + Math.random().toString(36).substring(2,10))
    }

    api.create = (device) => {
      let id = _generateId()
      _devices[id] = device

      let items = _store.getItem(_storeKey) || "{}"
      let payload = angular.extend({}, JSON.parse(items), _devices)

      _store.setItem(_storeKey, JSON.stringify(payload))

      return id
    }

    api.update = () => {

    }

    api.delete = () => {

    }

    api.getDevices = () => {
      let items = _store.getItem(_storeKey) || "{}"
      items = angular.extend({}, JSON.parse(items), _devices)

      let devices = []

      Object.keys(items).forEach((id) => {
        devices.push(items[id])
      })

      return devices
    }

    return api

  }
])
