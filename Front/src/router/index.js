import { createRouter, createWebHistory } from 'vue-router';
import RealTimeData from '../components/RealTimeData.vue';
import SessionList from '../components/SessionList.vue';

const routes = [
    {
      path: '/',
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
