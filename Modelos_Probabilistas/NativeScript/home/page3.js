const { fromObjectRecursive } = require('tns-core-modules/data/observable')

exports.autor_boton = args => {
    const button = args.object;
    const page = button.page;

    page.frame.navigate('/home/autor');
}

exports.onTap = args => {
    const button = args.object;
    const page = button.page;

    page.frame.navigate('/home/page2');
}