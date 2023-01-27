pipeline {
    agent any

    triggers {
        cron('0 3 * * 1-5')
    }

    options {
        skipStagesAfterUnstable()
    }

    stages {
        stage('Build') {
            steps {
                sh 'cmake -B ./build -DTESTING=On'
                sh 'cd build; make -j4'
            }
        }
        stage('Test'){
            steps {
                sh './run_tests.sh'
            }
        }
        stage('Generate coverage report'){
            steps {
                sh './generate_coverage-report.sh'
                sh "mkdir -p $JENKINS_HOME/userContent/libmcutils/coverage-reports"
                sh "cp -r coverage-report $JENKINS_HOME/userContent/libmcutils/coverage-reports/\$(date +%Y-%m-%d)_build-${env.BUILD_NUMBER}"
            }
        }
    }

    post {
        success {
            emailext (
                to: '$DEFAULT_RECIPIENTS'
                subject: "SUCCESSFUL: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
                body: """<p>SUCCESSFUL: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]':</p>
                <p>Check console output at &QUOT;<a href='${env.BUILD_URL}'>${env.JOB_NAME} [${env.BUILD_NUMBER}]</a>&QUOT;</p>""",
                mimeType: 'text/html'
            )
        }

        failure {
            emailext (
                to: '$DEFAULT_RECIPIENTS'
                subject: "FAILED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
                body: """<p>FAILED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]':</p>
                <p>Check console output at &QUOT;<a href='${env.BUILD_URL}'>${env.JOB_NAME} [${env.BUILD_NUMBER}]</a>&QUOT;</p>""",
                mimeType: 'text/html'
            )
        }
    }
}
