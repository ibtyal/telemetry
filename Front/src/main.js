import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import { createI18n } from 'vue-i18n'
import en from './locales/en.json'
import es from './locales/es.json'
import de from './locales/de.json'
import zh from './locales/zh.json'

// Configuración de i18n
const i18n = createI18n({
  locale: 'es', // Idioma por defecto
  messages: {
    en,
    es,
    de,
    zh
  }
})

const app = createApp(App)
app.use(router)
app.use(i18n)
app.mount('#app')

