FROM tomcat

WORKDIR /opt/tp_docker_2

COPY jenkins.war .
ENV JENKINS_HOME=/opt/tp_docker_2/jenkins

EXPOSE 8080

CMD [ "java", "-jar", "jenkins.war" ]
