# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

import os
import sys
basedir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, basedir)
sys.path.insert(0, basedir + os.sep + 'python')
c_autodoc_roots = [basedir + os.sep + 'c']
c_autodoc_compilation_args = ['-std=c11', '-DAMD_COMPILER=0']
js_source_path = basedir + os.sep + 'javascript'

project = 'Euler'
copyright = '2024, Olivia Appleton'
author = 'Olivia Appleton'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.githubpages',
    'sphinx.ext.graphviz',
    'sphinx.ext.inheritance_diagram',
    'sphinx.ext.mathjax',
    'sphinx.ext.todo',
    'sphinx_c_autodoc',
    # 'breathe',
    # 'javasphinx',
    # 'sphinx_autodoc_typehints',
    # 'sphinx_pyreverse',
    # 'sphinx_js',
    # 'sphinx_csharp',
]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

language = 'english'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

# -- Options for todo extension ----------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/todo.html#configuration

todo_include_todos = True
