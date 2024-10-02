<template>
  <div>
    <h2>{{ $t('sessions_registered') }}</h2>
    <ul>
      <li v-for="session in sessions" :key="session._id">
        <a :href="`https://www.vehiculoelectricosiima.com/download/${session._id}`" target="_blank">
          {{ formatDate(session.start_time) }}
        </a>
      </li>
    </ul>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  data() {
    return {
      sessions: []
    }
  },
  created() {
    this.fetchSessions()
  },
  methods: {
    async fetchSessions() {
      try {
        const response = await axios.get('https://www.vehiculoelectricosiima.com/sessions')
        this.sessions = response.data.sessions
      } catch (error) {
        console.error('Error fetching sessions:', error)
      }
    },
    formatDate(dateString) {
      const options = { year: 'numeric', month: 'long', day: 'numeric', hour: '2-digit', minute: '2-digit' }
      return new Date(dateString).toLocaleDateString(this.$i18n.locale, options)
    }
  }
}
</script>

<style>
/* Add some basic styling */
ul {
  list-style: none;
  padding: 0;
}

li {
  margin: 0.5em 0;
}

a {
  text-decoration: none;
  color: blue;
}

a:hover {
  text-decoration: underline;
}
</style>

