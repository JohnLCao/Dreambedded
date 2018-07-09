const app = angular.module('dreambedded')

import template from './navbar.hamlc'

app.directive('navbar', [
  () => {
    return {
      link: (scope, element, attr) => {
        console.log(scope, element, attr)
      },
      template: template()
    }
  }
])
