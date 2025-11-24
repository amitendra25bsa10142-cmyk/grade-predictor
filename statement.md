# Project Title
Student Performance Prediction Using Machine Learning

## Problem statement
Predict student academic performance (final exam score or grade band) from demographic, attendance, and past-assessment features to help instructors identify at-risk students early and recommend interventions.

## Scope of the project
- Input: student-level data (demographics, past scores, attendance, engagement metrics)
- Output: predicted final grade (regression) and risk category (classification: Low/Medium/High risk)
- Core ML pipeline: data cleaning, feature engineering, model training, evaluation, and deployment-ready inference script
- Not covered: full production deployment (but includes a lightweight inference API scaffold)

## Target users
- University instructors and academic advisors
- Student support teams
- Course coordinators interested in early-warning systems

## High-level features
- Data ingestion and validation module
- Feature engineering module (derived features like attendance rate, assignment completion ratio)
- Modeling module (train/test splits, baseline models, cross-validation)
- Evaluation and visualization (confusion matrix, ROC/AUC for classification; RMSE, MAE for regression)
- Simple Flask inference API for serving predictions
- Documentation, tests, and version control (Git) best practices
