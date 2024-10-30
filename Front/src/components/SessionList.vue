<template>
  <div>
    <h2>{{ $t("sessions_registered") }}</h2>
  </div>
  <div class="historial">
    <ul>
      <li v-for="file in files" :key="file">
        <a :href="`/api/download/${file}`" download>{{ file }}</a>
      </li>
    </ul>
  </div>
</template>

<script>
export default {
  data() {
    return {
      files: [],
    };
  },
  mounted() {
    fetch("/api/sessions")
      .then((response) => response.json())
      .then((data) => {
        this.files = data;
      });
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
