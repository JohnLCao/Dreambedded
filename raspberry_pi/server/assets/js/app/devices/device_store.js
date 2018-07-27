const app = angular.module('dreambedded')

app.service('DeviceStore', [
  () => {

    let _store = window.localStorage
    let _storeKey = 'dreambedded:devices'
    let api  = {}
    window.DeviceStore = api

    let _generateId = () => {
      return (Math.random().toString(36).substring(2,10) + Math.random().toString(36).substring(2,10))
    }

    api.create = (device) => {
      let id = _generateId()
      let items = _store.getItem(_storeKey) || "{}"
      let payload = JSON.parse(items)
      let item = {}
      item[id] = device
      payload = angular.extend({}, payload, item)

      _store.setItem(_storeKey, JSON.stringify(payload))

      return id
    }

    api.update = () => {

    }

    api.delete = () => {

    }

    api.getDevices = () => {
      let items = _store.getItem(_storeKey) || "{}"
      items = JSON.parse(items)

      let devices = []

      Object.keys(items).forEach((id) => {
        devices.push(
          angular.extend({}, items[id], { id: id })
        )
      })

      return devices
    }

    return api

  }
])
