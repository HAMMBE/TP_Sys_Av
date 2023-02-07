# EX2

1. Récupération des ressources.
    
    ```
    docker pull tomcat
    ```
    ```
    wget https://get.jenkins.io/war-stable/2.361.4/jenkins.war -O jenkins.war
    ```

2. Rédaction d'un fichier Dockerfile.
    ```Dockerfile
    FROM tomcat

    WORKDIR /opt/tp_docker_2

    COPY jenkins.war .
    ENV JENKINS_HOME=/opt/tp_docker_2/jenkins

    EXPOSE 8080

    CMD [ "java", "-jar", "jenkins.war" ]
    ```

3. Construction de l'image.
    ```
    docker build . -t tp_docker_2
    ```

4. Test du service.
    ```
    docker run -d -p 8080:8080 --name tp_docker_2 tp_docker_2
    ```
