pipeline {
    agent {
        docker { image 'libmcutils-build-env:1' }
    }

    environment {
        RECIPIENT_LIST = 'dev@marekcel.pl'
    }

    triggers {
        pollSCM('0 3 * * 1-5')
    }

    options {
        skipStagesAfterUnstable()
    }

    stages {
        stage('Build') {
            steps {
                sh 'cd misc; python3 ./build.py'
            }
        }
        stage('Test') {
            steps {
                sh 'cd misc; python3 ./run_tests.py'
            }
        }
        stage('Generate coverage report') {
            steps {
                sh 'cd misc; python3 ./generate_coverage-report.py'
            }
        }
    }

    post {
        success {
            emailext (
                to: "${env.RECIPIENT_LIST}",
                subject: "SUCCESS: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
                body: """<p>SUCCESS: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]':</p>
                <p>Check console output at <a href='${env.BUILD_URL}'>${env.JOB_NAME} [${env.BUILD_NUMBER}]</a></p>""",
                mimeType: 'text/html'
            )
        }

        failure {
            emailext (
                to: "${env.RECIPIENT_LIST}",
                subject: "FAILURE: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
                body: """<p>FAILURE: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]':</p>
                <p>Check console output at <a href='${env.BUILD_URL}'>${env.JOB_NAME} [${env.BUILD_NUMBER}]</a></p>""",
                mimeType: 'text/html'
            )
        }
    }
}
