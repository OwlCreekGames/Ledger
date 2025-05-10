# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Ledger'
copyright = '2025, Owl Creek Games'
author = 'Owl Creek Games'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['sphinx_immaterial', 'breathe']

templates_path = ['_templates']
exclude_patterns = []

docurls = ""

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_immaterial'
html_static_path = ['_static']

# -- Options for Doxygen integration ------------------------------------------

breathe_projects = {'ledger': './_doxygen/xml'}

breathe_default_project = 'ledger'

# -- Options for Immaterial ---------------------------------------------------
html_theme_options = {
    'repo_url': 'https://github.com/OwlCreekGames/Ledger'
}