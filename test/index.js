var tape = require ('tape')
tape('==================== sendto testsuite summary ====================', tests);
function tests (t){
  t.test('===== sendto buffers =====', require('./sendto'));
}
