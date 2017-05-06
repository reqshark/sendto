{'targets': [
    {
        'target_name': 'sendto',
        'include_dirs': [
            "<!(node -e \"require('nan')\")",
        ],
        'sources': [ 'binding.cc' ],
    }
]}
