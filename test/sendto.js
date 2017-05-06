var lib = require('..')

module.exports = function sendto (t) {
  t.test('sendto', out);
}

function out (t) {
  t.plan(1)
  var buf = new Buffer('Hello, world!')
  t.ok( Buffer.isBuffer(buf))
}
