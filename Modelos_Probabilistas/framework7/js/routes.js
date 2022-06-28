
import HomePage from '../pages/home.f7.html';
import AutorPage from '../pages/autor.f7.html';
import FormPage from '../pages/form.f7.html';

import infoPage from '../pages/info.f7.html';
import valuechainPage from '../pages/valuechain.f7.html';



import erpPage from '../pages/erp.f7.html';
import decPage from '../pages/dec.f7.html';


import DynamicRoutePage from '../pages/dynamic-route.f7.html';
import RequestAndLoad from '../pages/request-and-load.f7.html';
import NotFoundPage from '../pages/404.f7.html';

var routes = [
  {
    path: '/',
    component: HomePage,
  },
  {
    path: '/autor/',
    component: AutorPage,
  },
  {
    path: '/form/',
    component: FormPage,
  },
  {
    path: '/info/',
    component: infoPage,
  },
  {
    path: '/value/',
    component: valuechainPage,
  },
  {
    path: '/erp/',
    component: erpPage,
  },
  {
    path: '/dec/',
    component: decPage,
  },
  {
    path: '/form/',
    component: FormPage,
  },
  {
    path: '/dynamic-route/blog/:blogId/post/:postId/',
    component: DynamicRoutePage,
  },
  {

  },
  {
    path: '/request-and-load/user/:userId/',
    async: function ({ router, to, resolve }) {
      // App instance
      var app = router.app;

      // Show Preloader
      app.preloader.show();

      // User ID from request
      var userId = to.params.userId;

      // Simulate Ajax Request
      setTimeout(function () {
        // We got user data from request
        var user = {
          firstName: 'Vladimir',
          lastName: 'Kharlampidi',
          about: 'Hello, i am creator of Framework7! Hope you like it!',
          links: [
            {
              title: 'Framework7 Website',
              url: 'http://framework7.io',
            },
            {
              title: 'Framework7 Forum',
              url: 'http://forum.framework7.io',
            },
          ]
        };
        // Hide Preloader
        app.preloader.hide();

        // Resolve route to load page
        resolve(
          {
            component: RequestAndLoad,
          },
          {
            props: {
              user: user,
            }
          }
        );
      }, 1000);
    },
  },
  {
    path: '(.*)',
    component: NotFoundPage,
  },
];

export default routes;