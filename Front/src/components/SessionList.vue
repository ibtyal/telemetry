<template>
  <div>
    <h2>{{ $t("sessions_registered") }}</h2>
    <ul>
      <li v-for="file in files" :key="file">
        <!-- Enlace de descarga directamente al archivo -->
        <a :href="`/download/${file}`" :download="file">{{ file }}</a>
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
        const response = await axios.get("/sessions");
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
  width: 60%;
  max-height: 35%;
  height: auto;
  margin-top: 20px;
  margin-left: 5%;
  padding: 20px;
  border-radius: 10px;
  align-items: center;
  overflow-y: auto;
}
.historial ul {
  height: 450px;
  width: auto;
  overflow-y: auto;
  max-height: 35%;
}

.historial ul li {
  list-style: none;
  text-decoration: none;
}
</style>
