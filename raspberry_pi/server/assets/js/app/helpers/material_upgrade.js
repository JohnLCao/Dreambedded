const app = angular.module('dreambedded')

app.directive('materialUpgrade', [
  () => {
    return {
      link: (scope, element, attrs) => {
        setTimeout(() => {
          window.componentHandler.upgradeElements(element[0])
        })
      }
    }
  }
])
