# EX1 | Proposer un service

1. La récupération de l'image jenkins depuis le hub docker.
- `docker pull jenkins/jenkins:alpine`

2. Le démarrage du conteneur proposant le service.
- `docker run -d -p 8080:8080 --name=tp_docker_1 jenkins/jenkins:alpine`

3. La vérification de la disponibilité du service.
- ✅

4. L'arrêt du conteneur associé.
- `docker stop tp_docker_jenkins`
