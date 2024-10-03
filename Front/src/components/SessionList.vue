<template>
  <div class="historial">
    <h2>{{ $t("sessions_registered") }}</h2>
    <ul>
      <li v-for="file in files" :key="file">
        <a :href="`http://localhost:8000/download/${file}`" target="_blank">{{
          file
        }}</a>
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
  mounted() {
    // Llama al backend para obtener la lista de archivos
    axios
      .get("http://localhost:8000/sessions", {
        headers: {
          "Content-Type": "application/json",
          "Access-Control-Allow-Origin": "*",
        },
      })
      .then((response) => {
        this.files = response.data.files;
      })
      .catch((error) => {
        console.error("Error fetching session files:", error);
      });
  },
};
</script>

<style>
.historial {
  background-color: rgba(5, 13, 27, 0.836);
  width: 90%;
  height: auto;
  margin-top: 20px;
  margin-left: 5%;
  padding: 20px;
  border-radius: 10px;
}

.historial ul li {
  text-decoration: none;
  list-style: none;
}
</style>
