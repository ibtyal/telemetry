<template>
  <div>
    <h2>{{ $t("sessions_registered") }}</h2>
    <ul>
      <li v-for="file in files" :key="file">
        <!-- Enlace de descarga directamente al archivo -->
        <a :href="`/download/${file}`" target="_blank">
          {{ file }}
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
    this.fetchFiles();
  },
  methods: {
    async fetchFiles() {
      try {
        const response = await axios.get("http://siima.tech:8000/sessions");
        this.files = response.data.files;
      } catch (error) {
        console.error("Error fetching files:", error);
      }
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
