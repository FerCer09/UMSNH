const { fromObjectRecursive } = require('tns-core-modules/data/observable')

exports.regresar = args => {
    const button = args.object;
    const page = button.page;
    page.frame.navigate('/home/home-page');
}