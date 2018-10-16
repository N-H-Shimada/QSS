qc_options.color_by_phase = true;
qc_options.circle_scale = 0.5;

var qxy_bits = 4;
var counter_bits = 3;

qc.reset(qxy_bits + counter_bits);
var qxy = qint.new(qxy_bits, 'qxy');
var counter = qint.new(counter_bits, 'counter');

qxy.write(0);
qxy.hadamard();
counter.write(0);

// Just an example scene evaluation
function apply_shader2(target, condition)
{
    target.phase(180, 1|2, condition);
    
}

// A=16 0: なし
// A=15 1: target.phase(180, 1|2|4|8, condition);
// A=14 2: target.phase(180, 1|2|4, condition);
// A=12 4: target.phase(180, 1|2, condition);
// A=10 6: QCEngine
// A=8  8: target.phase(180, 1, condition); target.phase(180, 2, condition);
/* A=0  16:
 target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(2); target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(4); target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(2); target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(4);
 
 target.not(1); target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(2); target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(4); target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(2); target.phase(180, 1|2|4|8, condition); target.not(8); target.phase(180, 1|2|4|8, condition); target.not(8);
 target.not(4);
 target.not(1);
 */

/* 16(test):
 qc.phase(180, 1|2|4|8); qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(2); qc.phase(180, 1|2|4|8); qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(4); qc.phase(180, 1|2|4|8); qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(2); qc.phase(180, 1|2|4|8); qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(4);
 
 qc.not(1); qc.phase(180, 1|2|4|8);  qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(2); qc.phase(180, 1|2|4|8); qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(4); qc.phase(180, 1|2|4|8); qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(2); qc.phase(180, 1|2|4|8); qc.not(8); qc.phase(180, 1|2|4|8); qc.not(8);
 qc.not(4);
 qc.not(1);
 */

function do_iterations(target, counter, shader_func)
{
    var eval_count = 0;
    for (var bit = 0; bit < counter.numBits; ++bit)
    {
        for (var iter = 0; iter < (1 << bit); ++iter)
        {
            shader_func(target, counter.bits(1 << bit));
            qxy.Grover(counter.bits(1 << bit));
        }
    }
}

qc.write(0);
qc.hadamard();
do_iterations(qxy, counter, apply_shader2);
counter.phase(180,1); // (注意!!) これ絶対必要
