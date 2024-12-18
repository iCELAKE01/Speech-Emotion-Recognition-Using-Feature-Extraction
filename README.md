<p align="center">
    <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" align="center" width="30%">
</p>
<p align="center"><h1 align="center">SPEECH-EMOTION-RECOGNITION-USING-FEATURE-EXTRACTION</h1></p>
<p align="center">
	<em>Elevate your voice, unlock emotions.</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/license/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction?style=default&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
	<img src="https://img.shields.io/github/last-commit/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction?style=default&color=0080ff" alt="repo-language-count">
</p>
<p align="center"><!-- default option, no dependency badges. -->
</p>
<p align="center">
	<!-- default option, no dependency badges. -->
</p>
<br>

##  Table of Contents

- [ Overview](#-overview)
- [ Features](#-features)
- [ Project Structure](#-project-structure)
  - [ Project Index](#-project-index)
- [ Getting Started](#-getting-started)
  - [ Prerequisites](#-prerequisites)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
  - [ Testing](#-testing)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)

---

##  Overview

The Speech-Emotion-Recognition-Using-Feature-Extraction project solves the challenge of accurately detecting emotions from speech. Key features include interactive data preprocessing, model training, and performance evaluation. Ideal for researchers, developers, and anyone aiming to enhance voice-based applications with emotional intelligence.

---

##  Features

|      | Feature         | Summary                                                                                                                                                                                                 |
| :--- | :---:           | :---                                                                                                                                                                                                  |
| ⚙️  | **Architecture**  | <ul><li>The project is primarily implemented using Tensorflow and Jupyter Notebook, which allows for an interactive and flexible development environment while being able to leverage the most out of dedicated GPU hardware.</li><li>Data handling scripts are integrated with the main notebook to manage datasets efficiently, while the datsets are to be downloaded independently. More instructions below.</li><li>Machine learning models and visualization tools are modularly structured within the codebase.</li></ul> |
| 🔩 | **Code Quality**  | <ul><li>The project leverages Jupyter Notebooks for its primary development, which inherently supports a high level of readability and maintainability.</li><li>No explicit code quality metrics or linters are mentioned in the documentation, but the use of structured notebooks suggests adherence to best practices and in a lot of cases, parallel execution of the tasks to enable higher throughput.</li></ul> |
| 🔌 | **Integrations**  | <ul><li>The project integrates data handling scripts within Jupyter Notebooks to manage datasets efficiently.</li><li>The project utilises 4 other audio emotion calssified datasets which help in training the model in a clean manner.</li></ul> |
| 🧩 | **Modularity**    | <ul><li>Data preprocessing, model training, and performance evaluation are modularly structured within the project's files. It's main appeal is multithreaded unzipping of audio files which makes it able to extract the features from the provided datasets with significantly less wait time.</li><li>The use of pre-defined functions and classes from other modules streamlines the workflow and enhances modularity.</li></ul> |
| 🧪 | **Testing**       | <ul><li>No specific testing commands or frameworks are mentioned in the provided context, suggesting that testing might be done within the Jupyter Notebooks interactively.</li><li>The project's architecture does not explicitly support automated testing as of now but can be implemented later on as desired by the developer.</li></ul> |
| ⚡️  | **Performance**   | <ul><li>The project utilises Tensorflow libraries and CUDA/cuDNN support to leverage the massive compute capability of the dedicated GPU if available which helps in exponentially increasing the throughput of the training and answering the emotion of the provided audio It also utilises CPU based multithreading for unzipping of the datasers leading to significantly faster load times on the extraction.</li><li>The project's architecture is flexible enough to incorporate performance improvements as needed.</li></ul> |
| 🛡️ | **Security**      | <ul><li>Given the nature of Jupyter Notebooks, basic security practices should be followed (e.g., secure data handling).</li><li>The project's architecture does not explicitly address security concerns.</li></ul> |
| 📦 | **Dependencies**  | <ul><li>Conda - 24.9.2</li><li>Python - 3.10.3</li><li>jupyter_core - 5.7.2</li><li>keras - 2.10.0</li><li>Librosa - 0.10.2</li><li>Matplotlib - 3.9.2</li><li>Numpy - 1.26.4</li><li>Pandas - 2.2.2</li><li>PIP - 24.2</li><li>Seaborn - 0.13.2</li><li>Scikit-learn - 1.5.2</li><li>Tensorflow - 2.10.0</li><li>Scipy - 1.13.1</li><li>CuDNN</li></ul> |
| 🚀 | **Scalability**   | <ul><li>The project's architecture has two variations of scalability which can be achieved based on the fulfillment criteria. Better hardware, specifically a better GPU with more CUDA cores can help increase the throughput. On a more software level, better usage of code optimisation and elimination of possible redundant code can increase performance and reduce time taken for compute.</li></ul> |
```

### Additional Context:

---

##  Project Structure

```sh
└── Speech-Emotion-Recognition-Using-Feature-Extraction/
    ├── LICENSE
    ├── README.md
    └── speech-emotion-recognition.ipynb
```


###  Project Index
<details open>
	<summary><b><code>SPEECH-EMOTION-RECOGNITION-USING-FEATURE-EXTRACTION/</code></b></summary>
	<details> <!-- __root__ Submodule -->
		<summary><b>__root__</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction/blob/master/speech-emotion-recognition.ipynb'>speech-emotion-recognition.ipynb</a></b></td>
				<td>- The `speech-emotion-recognition.ipynb` file serves as a central notebook for implementing and evaluating speech emotion recognition models within the project<br>- This notebook integrates with the broader codebase to facilitate data preprocessing, model training, and performance evaluation<br>- It leverages the project's structured directory for accessing datasets and utilises pre-defined functions and classes from other modules to streamline the workflow.

The file is part of a larger architecture that includes data handling scripts, machine learning models, and visualization tools<br>- Its primary purpose is to provide an interactive environment for experimenting with different emotion recognition techniques and tuning model parameters, ultimately contributing to the development of robust speech emotion recognition capabilities within the project.</td>
			</tr>
			</table>
		</blockquote>
	</details>
</details>

---
##  Getting Started

###  Prerequisites

Before getting started with Speech-Emotion-Recognition-Using-Feature-Extraction, ensure your runtime environment meets the following requirements:

- **Programming Language:** Python


###  Installation

Install Speech-Emotion-Recognition-Using-Feature-Extraction using one of the following methods:

**Build from source:**

1. Clone the Speech-Emotion-Recognition-Using-Feature-Extraction repository:
```sh
 git clone https://github.com/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction
```

2. Navigate to the project directory:
```sh
 cd Speech-Emotion-Recognition-Using-Feature-Extraction
```

3. Install the project dependencies:
```sh
 pip install -r requirements.txt
```

##  Contributing

- **💬 [Join the Discussions](https://github.com/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction/discussions)**: Share your insights, provide feedback, or ask questions.
- **🐛 [Report Issues](https://github.com/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction/issues)**: Submit bugs found or log feature requests for the `Speech-Emotion-Recognition-Using-Feature-Extraction` project.
- **💡 [Submit Pull Requests](https://github.com/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to github**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com{/iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=iCELAKE01/Speech-Emotion-Recognition-Using-Feature-Extraction">
   </a>
</p>
</details>
---

##  Acknowledgments

- We acknowledge the use of the following datasets:
1. Ryerson Audio-Visual Database of Emotional Speech and Song (RAVDESS)
2. Crowd Sourced Emotional Multimodal Actors Dataset (CREMA-D)
3. Surrey Audio-Visual Expressed Emotion (SAVEE)
4. Toronto emotional speech set (TESS)
---
