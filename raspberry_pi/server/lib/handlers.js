const Bridge = require('./bridge')

const Handlers = {
  action: (message) => {
    Bridge.send("action", message, (err) => {
      console.log(err)
    })
  },

  __logger: (fn) => {
    let wrap = (msg) => {
      console.log("[LOGGER] ", msg)

      fn(msg)
    }

    return wrap
  }
}


module.exports = Handlers
