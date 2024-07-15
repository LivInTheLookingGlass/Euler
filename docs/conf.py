# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

from os import environ, path, sep
from subprocess import CalledProcessError, check_call
from sys import path as sys_path

from sphinxcontrib.domaintools import custom_domain
if 'TERMUX_VERSION' not in environ:
    from ghlinguist import linguist
    import matplotlib.pyplot as plt

basedir = path.abspath(path.join(path.dirname(__file__), '..'))
sys_path.insert(0, basedir)
sys_path.insert(0, basedir + sep + 'python')
js_source_path = basedir + sep + 'javascript'

project = 'Euler'
copyright = '2024, Olivia Appleton'
author = 'Olivia Appleton'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.extlinks',
    'sphinx.ext.githubpages',
    'sphinx.ext.graphviz',
    'sphinx.ext.inheritance_diagram',
    'sphinx.ext.intersphinx',
    'sphinx.ext.mathjax',
    'sphinx.ext.todo',
    # 'breathe',
    # 'javasphinx',
    # 'sphinx_autodoc_typehints',
    # 'sphinx_pyreverse',
    'sphinx_csharp.csharp',
    'sphinxcontrib.makedomain',
]

try:
    check_call(['rpm-ostree', '--version'])
    IS_SILVERBLUE = True
except Exception:
    IS_SILVERBLUE = False

if 'TERMUX_VERSION' not in environ and not IS_SILVERBLUE:
    extensions.append('sphinx_js')

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

extlinks = {'prob': ('https://projecteuler.net/problem=%s',
                     'Problem #%s')}

intersphinx_mapping = {'python': ('https://docs.python.org/3', None)}

def setup(app):
    if 'TERMUX_VERSION' not in environ:
        langs = linguist(basedir)
        labels = [lang[0] for lang in langs]
        sizes = [lang[1] for lang in langs]
        fig, ax = plt.subplots()
        ax.pie(sizes, labels=labels, autopct='%1.1f%%', labeldistance=None)
        plt.legend(title='Languages', loc='center right', bbox_to_anchor=(0.75, 0, 0.5, 1))
        plt.savefig("languages.svg", transparent=True)

    app.add_domain(custom_domain(
        "RustDomain",
        "rust",
        "Rust",
        {
            "fn": {
            },
            "struct": {
            },
            "var": {
            },
        }
    ))

