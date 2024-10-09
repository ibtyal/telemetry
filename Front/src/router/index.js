import { createRouter, createWebHistory } from 'vue-router';
import HomePage from "../components/HomePage.vue";
import RealTimeData from '../components/RealTimeData.vue';
import SessionList from '../components/SessionList.vue';

const routes = [
  {
    path: "/",
    name: "home",
    component: HomePage,
  },
    {
      path: '/realtime-data',
      name: 'RealTimeData',
      component: RealTimeData
    },
    {
      path: '/sessions',
      name: 'SessionList',
      component: SessionList
    }
]

const router = createRouter({
    history: createWebHistory(),
    routes
});

export default router;
