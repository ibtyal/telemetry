<template>
  <div>
    <h2>{{ $t("sessions_registered") }}</h2>
  </div>
  <div class="historial">
    <ul>
      <li v-for="file in files" :key="file">
        <a :href="`https://siima.tech/download/${file}`" target="_blank">
          {{ formatDate(file) }}
        </a>
      </li>
    </ul>
  </div>
</template>

<script>
import axios from "axios";

export default {
  data() {
    return {
      files: [],
    };
  },
  created() {
    this.fetchSessions();
  },
  methods: {
    async fetchSessions() {
      try {
        const response = await axios.get("https://siima.tech/sessions", {
          headers: {
            "Content-Type": "application/json",
            //          "Access-Control-Allow-Origin": "*"
          },
        });
        this.files = response.data.files;
      } catch (error) {
        console.error("Error fetching sessions:", error);
      }
    },
    formatDate(filename) {
      const options = {
        year: "numeric",
        month: "long",
        day: "numeric",
        hour: "2-digit",
        minute: "2-digit",
      };
      return new Date(dateString).toLocaleDateString(
        this.$i18n.locale,
        options
      );
    },
  },
};
</script>

<style>
.historial {
  background-color: rgba(5, 13, 27, 0.836);
  width: 70%;
  height: auto;
  margin-top: 20px;
  margin-left: 5%;
  padding: 20px;
  border-radius: 10px;
  align-items: center;
}
.historial ul {
  height: 450px;
  width: auto;
  overflow-y: auto;
}

.historial ul li {
  list-style: none;
  text-decoration: none;
}
</style>
